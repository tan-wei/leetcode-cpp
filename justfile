set shell := ["bash", "-eu", "-o", "pipefail", "-c"]

# Defaults (edit as needed)

build_type := "Debug"
preset := "conan-debug"
profile := "conan/clang23"
generator := "Ninja"
CC := "clang"
CXX := "clang++"
skip_test := "False"
cache_option := "ccache"
enable_cppcheck := "False"
enable_clang_tidy := "False"
enable_coverage := "False"
run_binary := "leetcode_cpp"
gcov := "auto"

# Show available recipes
help:
    @just --list

# Setup virtual environment using uv (from README)
venv:
    uv venv

sync:
    uv sync

pre-commit-install:
    uv run pre-commit install

conan-profile-detect:
    # idempotent: only run detect if the default profile file does not already exist
    if [ -f "$HOME/.conan2/profiles/default" ]; then echo "Conan profile 'default' exists -- skipping"; else uv run conan profile detect; fi

# One-shot setup: run venv, sync, pre-commit install and conan profile detect
setup: venv sync pre-commit-install conan-profile-detect
    @echo "Setup finished. To activate the virtualenv run: source .venv/bin/activate"

# Install dependencies via Conan (edit variables above before running)
conan-install:
    uv run conan install -pr:a default \
      -pr:h {{ profile }} \
      -c:a tools.cmake.cmaketoolchain:generator={{ generator }} \
      -c:h tools.build:compiler_executables='{"c": "{{ CC }}", "cpp": "{{ CXX }}"}' \
      -c:h tools.build:skip_test={{ skip_test }} \
      -s:h build_type={{ build_type }} -b missing .

# Activate virtualenv (prints instruction because sourcing won't persist)
activate:
    @echo "Run: source .venv/bin/activate"

# Configure project using CMake presets (adjust -D flags as needed)
configure:
    uv run cmake --preset {{ preset }} \
      -D ENABLE_CPPCHECK={{ enable_cppcheck }} \
      -D ENABLE_CLANG_TIDY={{ enable_clang_tidy }} \
      -D ENABLE_IPO=OFF \
      -D ENABLE_CACHE=OFF \
      -D CACHE_OPTION={{ cache_option }} \
      -D ENABLE_COVERAGE={{ enable_coverage }} \
      -D ENABLE_HARDENINGS=OFF \
      -D ENABLE_FORTIFY_SOURCE=OFF \
      -D ENABLE_ASAN=OFF \
      -D ENABLE_LSAN=OFF \
      -D ENABLE_UBSAN=OFF \
      -D ENABLE_TSAN=OFF

# Build and test
build id="":
    #!/usr/bin/env bash
    set -euo pipefail
    if [ -z {{ quote(id) }} ]; then
        uv run cmake --build --preset {{ preset }}
    else
        number=$(just _solution-id {{ quote(id) }})
        uv run cmake --build --preset {{ preset }} --target "leetcode_test_s${number}"
    fi

test id="":
    #!/usr/bin/env bash
    set -euo pipefail
    if [ -z {{ quote(id) }} ]; then
        uv run ctest --preset {{ preset }}
    else
        number=$(just _solution-id {{ quote(id) }})
        just build_type={{ build_type }} preset={{ preset }} build "$number"
        binary="./build/{{ build_type }}/leetcode_test_s${number}"
        if [ -f "${binary}.exe" ]; then binary="${binary}.exe"; fi
        uv run "$binary"
    fi

_solution-id id:
    #!/usr/bin/env bash
    set -euo pipefail
    id={{ quote(id) }}
    if [[ ! "$id" =~ ^[0-9]{1,4}$ ]] || (( 10#$id == 0 )); then
        echo "Invalid problem id: $id (expected 1-9999)" >&2
        exit 1
    fi
    printf -v number '%04d' "$((10#$id))"
    shopt -s nullglob
    sources=(src/solution/s"${number}"_*.cpp)
    if [ "${#sources[@]}" -ne 1 ]; then
        echo "Expected one solution for $number in src/solution, found ${#sources[@]}" >&2
        exit 1
    fi
    printf '%s\n' "$number"

# Run cppcheck using the generated compile_commands.json (optional: run `just configure` first)
cppcheck:
    @command -v cppcheck >/dev/null 2>&1 || { echo "cppcheck not found; install it (brew/apt)"; exit 2; }
    # Use compile_commands.json so cppcheck picks up include paths from CMake/Conan
    COMPILE_COMMANDS_PATH=build/{{ build_type }}/compile_commands.json; if [ ! -f "$COMPILE_COMMANDS_PATH" ]; then echo "compile_commands.json not found; run 'just configure' first"; exit 1; fi; cppcheck --project="$COMPILE_COMMANDS_PATH" -v --enable=all --check-level=exhaustive --inline-suppr --suppressions-list=cppcheck.suppressions || true

# Run the compiled leetcode_cpp executable. Depends on `build` so the binary
# is up-to-date. Override `run_binary` or `build_type` locally if needed.
run *args: build
    uv run ./build/{{ build_type }}/{{ run_binary }} {{ args }} ${RUN_ARGS:-}

# Regenerate compile_commands.json (compilation database) by re-running CMake
# configure. Run this after `just run solve <id>` or whenever new solution
# files are added so that clangd / your IDE picks up the new translation units.
comdb: configure
    @echo "compile_commands.json regenerated."

# Solve (move) problem <id> from src/problem/ to src/solution/, then regenerate
# the compilation database so the new file appears in compile_commands.json.
solve id:
    just run solve {{id}}
    just comdb

# Cleaning targets
# - `clean-setup`: remove setup artifacts (virtualenv, pre-commit hooks)
# - `clean-build`: remove build artifacts
# - `clean-all`: remove both setup and build artifacts

# Keep `clean` as an alias to `clean-build` for backwards compatibility.
clean-setup:
    # If a virtualenv exists, attempt to uninstall pre-commit (without creating a venv), then remove it
    if [ -d .venv ]; then if [ -x .venv/bin/pre-commit ]; then .venv/bin/pre-commit uninstall || true; elif command -v uv >/dev/null 2>&1; then uv run pre-commit uninstall || true; fi; fi; rm -rf .venv/ || true

clean-build:
    # Remove common build directories and artifacts
    for d in build "{{ build_type }}" Debug Release "build/{{ build_type }}" build/Debug build/Release build/bin; do if [ -d "$d" ]; then rm -rf "$d" || true; fi; done
    # remove CMake-generated files in project root if present
    rm -f CMakeCache.txt cmake_install.cmake compile_commands.json CMakeUserPresets.json CMakeSettings.json || true

clean-all: clean-setup clean-build

clean: clean-build

# Configure, build, test, and collect coverage for the current platform.
coverage id="":
    @if [ -n {{ quote(id) }} ]; then just _solution-id {{ quote(id) }} >/dev/null; fi
    @just build_type={{ build_type }} preset={{ preset }} enable_cppcheck={{ enable_cppcheck }} enable_clang_tidy={{ enable_clang_tidy }} enable_coverage=True cache_option={{ cache_option }} configure
    @just build_type={{ build_type }} preset={{ preset }} build {{ quote(id) }}
    @just build_type={{ build_type }} preset={{ preset }} CXX={{ CXX }} gcov='{{ gcov }}' coverage-report {{ quote(id) }}

# Collect coverage from an already-built coverage configuration.
coverage-report id="":
    #!/usr/bin/env bash
    set -euo pipefail
    report_dir=coverage
    test_command=(uv run ctest --preset {{ preset }})
    coverage_args=()
    source_args=()
    if [ -n {{ quote(id) }} ]; then
        number=$(just _solution-id {{ quote(id) }})
        report_dir="coverage/$number"
        binary="./build/{{ build_type }}/leetcode_test_s${number}"
        if [ -f "${binary}.exe" ]; then binary="${binary}.exe"; fi
        test_command=(uv run "$binary")
        coverage_args=("build/{{ build_type }}/CMakeFiles/leetcode_test_s${number}.dir"
            --cobertura "$report_dir/cobertura.xml" --html-nested "$report_dir/html"
            --sonarqube "$report_dir/sonarqube.xml" --coveralls "$report_dir/coveralls.json")
        source_args=(--sources "*s${number}_*.cpp")
    fi
    mkdir -p "$report_dir"
    if [ "${OS:-}" = "Windows_NT" ]; then
        if ! command -v OpenCppCoverage >/dev/null 2>&1; then echo "OpenCppCoverage not found; install it to collect MSVC coverage"; exit 2; fi
        OpenCppCoverage --export_type "cobertura:$report_dir/cobertura.xml" "${source_args[@]}" --cover_children -- "${test_command[@]}"
    else
        selected_gcov='{{ gcov }}'
        if [ "$selected_gcov" = "auto" ] || [ -z "$selected_gcov" ]; then
            if [ -n "${GCOV:-}" ]; then selected_gcov="$GCOV"
            elif [[ "{{ CXX }}" == *clang* ]] && command -v llvm-cov >/dev/null 2>&1; then selected_gcov="llvm-cov gcov"
            else selected_gcov="gcov"; fi
        fi
        "${test_command[@]}"
        uv run gcovr --gcov-executable "$selected_gcov" "${coverage_args[@]}"
    fi

# Format C/C++ sources under src/ using clang-format
fmt:
    if ! command -v clang-format >/dev/null 2>&1; then echo "clang-format not found; install clang-format to use just fmt"; exit 2; fi
    find src -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) -print0 | xargs -0 clang-format -i
    @echo "Formatted C/C++ sources under src/"

# Default task
default: help

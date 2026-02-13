set shell := ["bash", "-eu", "-o", "pipefail", "-c"]

# Defaults (edit as needed)
build_type := "Debug" # choices: "Debug" "Release" "RelWithDebInfo" "MinSizeRel"
preset := "conan-debug" # choices: "conan-debug" "conan-release"
profile := "conan/clang21" # choices: "conan/gcc15" "conan/clang21" "conan/default"
generator := "Ninja" # choices: "Ninja" "Unix Makefiles"
CC := "clang" # choices: "gcc" "clang"
CXX := "clang++" # choices: "g++" "clang++"
skip_test := "False" # choices: "True" "False"
cache_option := "ccache" # choices: "ccache" "sccache" "none"
enable_cppcheck := "False" # choices: "True" "False"
enable_clang_tidy := "False" # choices: "True" "False"
enable_coverage := "False" # choices: "True" "False"
run_binary := "leetcode_cpp" # executable name produced by the build

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
	  -pr:h {{profile}} \
	  -c:a tools.cmake.cmaketoolchain:generator={{generator}} \
	  -c:h tools.build:compiler_executables='{"c": "{{CC}}", "cpp": "{{CXX}}"}' \
	  -c:h tools.build:skip_test={{skip_test}} \
	  -s:h build_type={{build_type}} -b missing .

# Activate virtualenv (prints instruction because sourcing won't persist)
activate:
	@echo "Run: source .venv/bin/activate"

# Configure project using CMake presets (adjust -D flags as needed)
configure:
	uv run cmake --preset {{preset}} \
	  -D ENABLE_CPPCHECK={{enable_cppcheck}} \
	  -D ENABLE_CLANG_TIDY={{enable_clang_tidy}} \
	  -D ENABLE_IPO=OFF \
	  -D ENABLE_CACHE=OFF \
	  -D CACHE_OPTION={{cache_option}} \
	  -D ENABLE_COVERAGE={{enable_coverage}} \
	  -D ENABLE_HARDENINGS=OFF \
	  -D ENABLE_FORTIFY_SOURCE=OFF \
	  -D ENABLE_ASAN=OFF \
	  -D ENABLE_LSAN=OFF \
	  -D ENABLE_UBSAN=OFF \
	  -D ENABLE_TSAN=OFF

# Build and test
build:
	uv run cmake --build --preset {{preset}}

test:
	uv run ctest --preset {{preset}}

# Run cppcheck using the generated compile_commands.json (optional: run `just configure` first)
cppcheck:
	@command -v cppcheck >/dev/null 2>&1 || { echo "cppcheck not found; install it (brew/apt)"; exit 2; }
	# Use compile_commands.json so cppcheck picks up include paths from CMake/Conan
	COMPILE_COMMANDS_PATH=build/{{build_type}}/compile_commands.json; if [ ! -f "$COMPILE_COMMANDS_PATH" ]; then echo "compile_commands.json not found; run 'just configure' first"; exit 1; fi; cppcheck --project="$COMPILE_COMMANDS_PATH" -v --enable=all --check-level=exhaustive --inline-suppr --suppressions-list=cppcheck.suppressions || true

# Run the compiled leetcode_cpp executable. Depends on `build` so the binary
# is up-to-date. Override `run_binary` or `build_type` locally if needed.
run: build
	uv run ./build/{{build_type}}/{{run_binary}} ${RUN_ARGS:-}

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
	for d in build "{{build_type}}" Debug Release "build/{{build_type}}" build/Debug build/Release build/bin; do if [ -d "$d" ]; then rm -rf "$d" || true; fi; done
	# remove CMake-generated files in project root if present
	rm -f CMakeCache.txt cmake_install.cmake compile_commands.json CMakeUserPresets.json CMakeSettings.json || true

clean-all: clean-setup clean-build

clean: clean-build

# Collect coverage (use appropriate gcov value for your toolchain)
coverage:
	GCOV="gcov" uv run gcovr

# Format C/C++ sources under src/ using clang-format
fmt:
	if ! command -v clang-format >/dev/null 2>&1; then echo "clang-format not found; install clang-format to use just fmt"; exit 2; fi
	find src -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) -print0 | xargs -0 clang-format -i
	@echo "Formatted C/C++ sources under src/"

# Default task
default: help

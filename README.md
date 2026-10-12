# My Leetcode Solution in C++

[![CI](https://github.com/tan-wei/leetcode-cpp/actions/workflows/ci.yml/badge.svg)](https://github.com/tan-wei/leetcode-cpp/actions/workflows/ci.yml)
[![Coverage](https://codecov.io/gh/tan-wei/leetcode-cpp/graph/badge.svg)](https://codecov.io/gh/tan-wei/leetcode-cpp)

NOTE: Insipired by [original repository](https://github.com/tan-wei/leetcode-rust), thanks the original author and contributors of it!

## How to use

We use `just` to make it easy to install, run and test:
  1. `just setup`: Setup all enviroment with `uv`
  2. `just conan-install`: Install all dependencies by `conan`
  3. `just configure`: Do configure for `CMake`
  4. `just build`: Build the whole project
  5. `just run`: Run the main problem get program. With no arguments it stays interactive; with arguments it runs the command directly.
  6. `just test`: Run tests for whole projects
  7. `just cppcheck`: Run cppcheck
  8. `just coverage`: Configure with coverage enabled, build, test, and write reports under `coverage/`
  9. `just clean-all`: Remove all generated files


## Commit Message Convention

Commit messages must follow [Conventional Commits](https://www.conventionalcommits.org/) with the following rules enforced by `commitlint` (see `.commitlintrc.js`):

### Format

```
<type>(<scope>): <subject>
```

### Allowed types (`type-enum`)

- `solve` - add a solution for a problem
- `retry` - retry a previously failed submission (see scope rules below)
- `skip` - skip a problem
- `refactor`, `docs`, `test`, `revert`, `perf`, `build`, `chore`, `fix`, `ci`, `style` - conventional types

### Scope rules (`scope-format`)

Problem-related types (`solve`, `retry`, `skip`) require a 4-digit problem id as scope (e.g. `solve(0042)`).

In addition, the `retry` type must also append the failure result code, separated by a comma:

- `WA` - Wrong Answer
- `TLE` - Time Limit Exceeded
- `OLE` - Output Limit Exceeded
- `MLE` - Memory Limit Exceeded
- `RE` - Runtime Error
- `PE` - Presentation Error
- `CE` - Compile Error
- `CREDIT`

Example: `retry(0001,WA)`

Other types have no special scope validation.

### Other rules

- Header subject is limited to 50 characters (warning)
- Body lines are limited to 72 characters (warning)
- Subject case is not enforced (both `Do it` and `do it` are accepted)


## Usage

* Remove all the solution .cpp
* Clean all files in *src/solution*
* Start your leetcode journey by typing `just run` and then input the question id
* Fetch a problem directly with `just run {question_id}`
* To solve a problem (we should start the problem first), use `just run solve {question_id}` or enter `solve {question_id}` after `just run`
* To passby cloudflare, please `cp .env.smaple .env`, and set `LEETCODE_COOKIE` with your cookie (could be find in Firefox or Chrome console)

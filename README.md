# My Leetcode Solution in C++

NOTE: Insipired by [original repository](https://github.com/tan-wei/leetcode-rust), thanks the original author and contributors of it!

## How to use

We use `just` to make it easy to install, run and test:
  1. `just setup`: Setup all enviroment with `uv`
  2. `just conan-install`: Install all dependencies by `conan`
  3. `just configure`: Do configure for `CMake`
  4. `just build`: Build the whole project
  5. `just run`: Run the main problem get program, fetch and solve them!
  6. `just test`: Run tests for whole projects
  7. `just cppcheck`: Run cppcheck
  8. `just clean-all`: Remove all generated files


## Usage

* Remove all the solution .cpp
* Clean all files in *src/solution*
* Start your leetcode journey in rust by typing `just run` and then input the question id
* To solve a problem (we should start the problem first), input `solve {question_id}`
* To passby cloudflare, please `cp .env.smaple .env`, and set `LEETCODE_COOKIE` with your cookie (could be find in Firefox or Chrome console)

# w++ "$1.cpp" -o "$1"
cc_file=$(find . -type f -name "*.cc")
in_file=$(find . -type f -name "*.in")
g++ -std=c++20 -pedantic -Wall -Wextra -Weffc++ "$cc_file" -o "prog"
"./prog" < "$in_file"

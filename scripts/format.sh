cd ..
find . -name "*.cpp" -or -name "*.h" -or -name "*.c" | xargs clang-format -i
cd -

#!/usr/bin/env bash

# Function to display usage information
print_usage() {
    echo "Usage: $0 [command] [-a arch1,arch2,...] [-s size1,size2,...]"
    echo
    echo "Commands:"
    echo "  clean    Clean build directories"
    echo "  build    Build projects (default command)"
    echo
    echo "Options:"
    echo "  -a: Comma-separated list of architectures"
    echo "  -s: Comma-separated list of sizes"
    echo
    echo "Environment variables:"
    echo "  AM_HOME     Required. Root directory of AM project"
    echo "  ARCH        Architecture to build for (overrides -a)"
    echo "  MAKEFLAGS   Make flags (default: -j\$(nproc))"
    echo "  mainargs    Build arguments (overrides -s)"
    exit 1
}

# Default values as arrays
declare -a archs=("native")
declare -a sizes=("test" "ref")

# Set default make flags if not specified
MAKEFLAGS=${MAKEFLAGS:="-j$(nproc)"}

# Function to convert comma-separated string to array
convert_to_array() {
    local result=()
    IFS=',' read -ra result <<< "$1"
    echo "${result[@]}"
}

# Function to iterate over architectures and sizes
for_each_arch_size() {
    local callback=$1
    for arch in "${archs[@]}"; do
        export ARCH="$arch"
        for size in "${sizes[@]}"; do
            export mainargs="$size"
            $callback
        done
    done
}

# Clean callback function
do_clean() {
    make clean || true
    make -C "$AM_HOME" clean || true
}

# Build callback function
do_build_one() {
    if [ "$mainargs" = "${sizes[0]}" ]; then
        make -C "$AM_HOME" $MAKEFLAGS install || exit 1
    fi
    make $MAKEFLAGS all || exit 1
}

# Check if first argument is a command
command="build"
if [ $# -gt 0 ]; then
    case "$1" in
        clean|build)
            command="$1"
            shift
            ;;
    esac
fi

# Parse remaining arguments
while getopts "a:s:h" opt; do
    case $opt in
        a)
            archs=($(convert_to_array "$OPTARG"))
            ;;
        s)
            sizes=($(convert_to_array "$OPTARG"))
            ;;
        h)
            print_usage
            ;;
        \?)
            echo "Invalid option: -$OPTARG"
            print_usage
            ;;
    esac
done

# Check if AM_HOME is set
if [ -z "$AM_HOME" ]; then
    echo "Error: AM_HOME environment variable is not set"
    exit 1
fi

# Execute requested command
case "$command" in
    clean)
        for_each_arch_size do_clean
        ;;
    build)
        for_each_arch_size do_build_one
        ;;
esac

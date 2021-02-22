clear
# echo "Removing old binaries..."
make clean
echo "Compiling..."
make
echo "Setting permissions..."
chmod +x ./build/final_program
echo "Running binary..."
echo ""
echo "./build/final_program"
# -ex=run : Run immediately
# --args : Pass args to function, not to gdb
gdb -ex=run --args ./build/final_program $1 $2 $3

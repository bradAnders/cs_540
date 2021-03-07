clear
# echo "Removing old binaries..."
make clean
echo "Compiling..."
make
echo "Setting permissions..."
chmod +x ./build/main3.out
echo "Running binary..."
echo ""
echo "./build/main3.out"
# -ex=run : Run immediately
# --args : Pass args to function, not to gdb
gdb -ex=run --args ./build/main3.out $1 $2 $3

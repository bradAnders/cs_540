clear
# echo "Removing old binaries..."
# make clean
echo "Compiling..."
make all
echo "Setting permissions..."
chmod +x ./src/main.app
echo "Running binary..."
echo ""
echo "./src/main.app"
./src/main.app $1 $2 $3

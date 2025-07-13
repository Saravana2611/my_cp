rm -rf build/
rm -rf second.txt
echo "build/ directory removed"
cmake -S . -B build/

echo "Calling make cmd"
make -C build/

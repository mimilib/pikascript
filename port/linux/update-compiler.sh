ROOT=$PWD
cd ../../tools/pikaCompiler
cargo clean
cargo build
cd $ROOT
cp ../../tools/pikaCompiler/rust-msc-latest-linux package/pikascript/rust-msc-latest-linux
cp ../../tools/pikaCompiler/target/debug/rust-msc package/pikascript/rust-msc-latest-linux
# cp ../../tools/pikaCompiler/target/debug/rust-msc.exe package/pikascript/rust-msc-latest-win10.exe
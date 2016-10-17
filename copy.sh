cd ~/workspace/liblinux/base
make install 
cd ~/workspace/liblinux/net
make install
cd ~/workspace/json/src
make install

rm ~/workspace/ldb/base/*
rm ~/workspace/ldb/net/*
rm ~/workspace/ldb/json/*
cp ~/workspace/liblinux/base/bin/* ~/workspace/ldb/base
cp ~/workspace/liblinux/net/bin/* ~/workspace/ldb/net
cp ~/workspace/json/src/bin/* ~/workspace/ldb/json

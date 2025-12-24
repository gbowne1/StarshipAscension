# 1. Update your package list
sudo apt update

# 2. Upgrade your package list
sudo apt upgrade -y

# 3. Install glog and its dependencies (gflags, protobuf)
sudo apt install -y libgoogle-glog-dev libgflags-dev protobuf-compiler libprotobuf-dev

# 4. (Optional) If you have issues, ensure build essentials are present
sudo apt install build-essential cmake -y
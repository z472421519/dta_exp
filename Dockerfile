# 基于 Ubuntu 20.04 的 Docker 镜像
FROM ubuntu:20.04

# 设置环境变量（可选）
ENV TZ=Asia/Shanghai
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    echo "Asia/Shanghai" > /etc/timezone

# 更新源并安装软件包
RUN apt-get update && \
    apt-get install -y \
    cmake python3 g++ wget python vim git

WORKDIR /opt/shared

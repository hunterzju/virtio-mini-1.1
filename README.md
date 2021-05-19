# virtio-mini-1.1
[virtio-mini](https://github.com/matthias-prangl/virtio-mini)实现了一个最简单的virtio示例设备`virtio-mini`，可以模拟virtio的读写过程。项目包含了virtio前端和后端，不过适配的是qemu3.0和linux-4.x内核，不支持最新的virtio1.1标准。
本项目在学习virtio过程中将virtio-mini适配到qemu-5.2和linux-5.10内核，以支持virtio-1.1。

## virtio-backend
后端实现在qemu-5.2中，主要将`virtio-mini`和`virtio-mini-pci`的实现，并在`virtio.h`中开启了`packed_queue`特征。
使用qmd命令`device_add virtio-mini`在qemu后端中添加`virtio-mini`设备。
在qemu编译过程中需要添加编译选项`--enable-virtio_mini`

## virtio-frontend
前端实现适配linux-5.10的内核模块，采用ubuntu-20镜像并把内核升级到5.10后编译出内核模块`virtio-mini.ko`，采用`insmod`加载后会生成一个chardev`/proc/virtio-mini-x`，通过读写该文件实现向后端buffer中写入或者读出内容。

## Todolist
[] 完成virtio-mini实现的文档总结
[] 结合dpdk学习

## 参考资料：
* virtio虚拟化：https://zhuanlan.zhihu.com/p/68154666
* virtio-1.1规范：https://docs.oasis-open.org/virtio/virtio/v1.1/cs01/virtio-v1.1-cs01.pdf
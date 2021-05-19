./build/qemu-system-x86_64 -m 2048 ../qemu-run/ubuntu18.img -serial mon:stdio -net user,hostfwd=tcp::2222-:22 -net nic

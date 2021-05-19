#ifndef QEMU_VIRTIO_MINI_H
#define QEMU_VIRTIO_MINI_H_

#include "standard-headers/linux/virtio_mini.h"

#define TYPE_VIRTIO_MINI "virtio-mini-device"
#define VIRTIO_MINI(obj) \
        OBJECT_CHECK(VirtIOMini, (obj), TYPE_VIRTIO_MINI)

void virtio_mini_print(const char *fmt, ...) GCC_FMT_ATTR(1,2);

typedef struct VirtIOMini {
    VirtIODevice parent_obj;
    VirtQueue *vq_tx;
    VirtQueue *vq_rx;
    void *rcv_bufs[VIRTIO_MINI_BUFFERS];
    unsigned int rcv_count;
} VirtIOMini;

#endif
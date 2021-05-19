#ifndef QEMU_VIRTIO_MINI_PCI_H
#define QEMU_VIRTIO_MINI_PCI_H

#include "hw/virtio/virtio-pci.h"
#include "hw/virtio/virtio-mini.h"
#include "qom/object.h"

typedef struct VirtIOMiniPCI VirtIOMiniPCI;

#define TYPE_VIRTIO_MINI_PCI "virtio-mini-pci"
#define VIRTIO_MINI_PCI(obj) \
        OBJECT_CHECK(VirtIOMiniPCI, (obj), TYPE_VIRTIO_MINI_PCI)

struct VirtIOMiniPCI {
    VirtIOPCIProxy parent_obj;
    VirtIOMini vdev;
};

#endif
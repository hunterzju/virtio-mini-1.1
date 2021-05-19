#include "qemu/osdep.h"
#include "virtio-mini-pci.h"
#include "qapi/error.h"
#include "qapi/qapi-events-machine.h"
#include "qapi/qapi-events-misc.h"

static void virtio_mini_pci_realize(VirtIOPCIProxy *vpci_dev, Error **errp)
{
    VirtIOMiniPCI *vmini = VIRTIO_MINI_PCI(vpci_dev);
    DeviceState *vdev = DEVICE(&vmini->vdev);
    Error *err = NULL;

    virtio_pci_force_virtio_1(&(vmini->parent_obj));
    qdev_set_parent_bus(vdev, BUS(&vpci_dev->bus), &err);
    if(err){
        error_propagate(errp, err);
        return ;
    }
    object_property_set_bool(OBJECT(vdev), "realized", true, &err);
    if(err){
        error_propagate(errp, err);
        return ;
    }
}

static void virtio_mini_pci_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    VirtioPCIClass *k = VIRTIO_PCI_CLASS(klass);
    PCIDeviceClass *pcidev_k = PCI_DEVICE_CLASS(klass);

    k->realize = virtio_mini_pci_realize;
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);

    pcidev_k->vendor_id = PCI_VENDOR_ID_REDHAT_QUMRANET;
    pcidev_k->device_id = PCI_DEVICE_ID_VIRTIO_MINI;
    pcidev_k->revision = VIRTIO_PCI_ABI_VERSION;
    pcidev_k->class_id = PCI_CLASS_OTHERS;
}

static void virtio_mini_initfn(Object *obj)
{
    VirtIOMiniPCI *dev = VIRTIO_MINI_PCI(obj);
    virtio_instance_init_common(obj, &dev->vdev, sizeof(dev->vdev),
                                TYPE_VIRTIO_MINI);
}

// static const TypeInfo virtio_mini_pci_info = {
//     .name = TYPE_VIRTIO_MINI_PCI,
//     .parent = TYPE_VIRTIO_PCI,
//     .instance_size = sizeof(VirtIOMiniPCI),
//     .instance_init = virtio_mini_initfn,
//     .class_init = virtio_mini_pci_class_init,
// };

static const VirtioPCIDeviceTypeInfo virtio_mini_pci_info = {
    // .base_name = TYPE_VIRTIO_MINI_PCI,
    .generic_name           = "virtio-mini-pci",
    // .transitional_name      = "virtio-mini-pci-transitional",
    // .non_transitional_name  = "virtio-mini-pci-non-transitional",
    .instance_size = sizeof(VirtIOMiniPCI),
    .instance_init = virtio_mini_initfn,
    .class_init    = virtio_mini_pci_class_init,
};

static void virtio_mini_pci_register(void)
{
    virtio_pci_types_register(&virtio_mini_pci_info);
}

// static void virtio_mini_pci_register(void)
// {
//     type_register_static(&virtio_mini_pci_info);
// }

type_init(virtio_mini_pci_register);

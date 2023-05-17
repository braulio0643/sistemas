#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#define DEVICE_NAME "nulo"
static ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
	// Completar
	return 0;
}

static ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
	// Completar
	return s;
}

static struct file_operations nulo_operaciones = {
	// Completar
	.owner = THIS_MODULE,
	.read = nulo_read,
	.write = nulo_write,
};

static dev_t num;
static struct cdev sist;
static struct class *mi_class;

static int __init nulo_init(void) {
	// Completar
	cdev_init(&sist , &nulo_operaciones);
	alloc_chrdev_region(&num, 0,1, DEVICE_NAME);
	cdev_add(&sist, num, 1);
	
	mi_class = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(mi_class, NULL, num, NULL, DEVICE_NAME);

	return 0;
}

static void __exit nulo_exit(void) {
	device_destroy(mi_class, num);
	class_destroy(mi_class);

	unregister_chrdev_region(num, 1);
	cdev_del(&sist);
	
	// Completar
}

// Completar
module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de '/dev/null'");
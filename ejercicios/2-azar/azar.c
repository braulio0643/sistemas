#include <linux/init.h>
#include <linux/module.h> // THIS_MODULE
#include <linux/kernel.h> // Kernel cosas
#include <linux/fs.h>     // File operations
#include <linux/cdev.h>   // Char devices
#include <linux/device.h> // Nodos filesystem
#include <linux/uaccess.h> // copy_to_user
#include <linux/slab.h>    // kmalloc
#include <linux/random.h>  // get_random_bytes
#include "string.h"

// Completar
#define DEVICE_NAME "azar"


static dev_t num;
static struct cdev sist;
static struct class *mi_class
int res; 

static ssize_t azar_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
	// Completar
    void *buffer = mkmalloc(s+1, GFP_KERNEL);
    get_random_bytes(res, s);
    snprintf(buffer, s, "%d\n", res);
    copy_to_user(data, buffer, s);
	return 0;
}

static ssize_t azar_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
	// Completar
    void *buffer = mkmalloc(s+1, GFP_KERNEL);
    copy_from_user(buffer, data, s);
    buffer[s] = '\0';
    int numero = kstrtoint(buffer, 10, &res);
    kfree(buffer);
    if(numero == 0){
        return s;
    } else {
        return numero;
    }

	return s;
}

static struct file_operations azar_operaciones = {
	// Completar
	.owner = THIS_MODULE,
	.read = azar_read,
	.write = azar_write,
};
;


static int __init azar_init(void) {
	// Completar
    
    
	cdev_init(&sist , &azar_operaciones);
	alloc_chrdev_region(&num, 0,1, DEVICE_NAME);
	cdev_add(&sist, num, 1);
	
	mi_class = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(mi_class, NULL, num, NULL, DEVICE_NAME);

	return 0;
}

static void __exit azar_exit(void) {
	device_destroy(mi_class, num);
	class_destroy(mi_class);

	unregister_chrdev_region(num, 1);
	cdev_del(&sist);
    kfree(memDinamica);
	
	// Completar
}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Generador de números al azar");
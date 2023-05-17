#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xf0596884, "module_layout" },
	{ 0x8ad389ec, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xc8fa02e9, "class_destroy" },
	{ 0x2b5009ef, "device_destroy" },
	{ 0x1336a944, "device_create" },
	{ 0x9214df3a, "__class_create" },
	{ 0x5445ebff, "cdev_add" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x40446db6, "cdev_init" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


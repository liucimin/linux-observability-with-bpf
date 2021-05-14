
## first make the dir and mount bpf

```shell

mount -t bpf /sys/fs/bpf /sys/fs/bpf
mkdir /sys/fs/bpf/lcm

```


## reference



calico:

	https://docs.projectcalico.org/maintenance/ebpf/enabling-bpf
	
	
	(calico bpf 内核部分)https://github.com/projectcalico/felix/tree/master/bpf-gpl
	
	
	(calico bpf golang控制面部分)https://github.com/projectcalico/felix/tree/master/bpf



## 学习记录

  本来准备使用书上的用法，在用户空间创建map，内核一起更改，但是一直没找到内核怎么使用用户空间创建的map，如果反过来就很轻易使用。
    stackoverflow有相似问题，但是看不到最终结论
    
        https://stackoverflow.com/questions/57628432/ebpf-maps-for-one-element-map-type-and-kernel-user-space-communication
	
	

   查了下calico的源码，发现这部分还是内核来初始化map，
   
   控制面(用户空间)利用bpftool repin 这些map，
   
   如果pin文件还在则通过文件找到对应的map的fd来操作，
   
   如果文件都不在了，则找对应的map来repin，同时获得fd。
   
   这里有个疑惑，如果内核态的重新加载，则会还会出来同名的map，但是map id不一样，与之前pin的持久化的map已经不是同一个map了（bpftool map list -j）,
   
   而之前的bpf fs文件不删除文件存在则会读取该pin的fd，这样用户态在用老的map，而内核在更新新的map，这块calico还没看到怎么处理的，
   
   按照我的想法是会去删除这个pin文件.
   
   查阅bpf samples，发现xdp的一个demo就是这么玩的：
   
   
   https://github.com/netoptimizer/prototype-kernel/blob/master/kernel/samples/bpf/xdp_ddos01_blacklist_user.c#L78
   
   目前觉得clico可能就是这样。。
   
   
   https://prototype-kernel.readthedocs.io/en/latest/bpf/ebpf_maps.html#export-map-to-filesystem
   
   也主要讲是在usernamespace共享map，没说内核态共享：
```
When Interacting with maps from Userspace a file descriptor is needed. 
There are two methods for sharing this file descriptor.

By passing it over Unix-domain sockets.
Exporting the map to a special bpf filesystem.
Option 2, exporting or pinning the map through the filesystem is more convenient and easier than option 1. 
Thus, this document will focus on option 2.

Todo

Describe the API for bpf_obj_pin and bpf_obj_get. 
Usage examples available in XDP blacklist for bpf_obj_pin() and XDP blacklist cmdline tool show use of bpf_obj_get().

Todo

add link to Daniel’s TC example of using Unix-domain sockets.

```

	新发现：
            可以用bpftool prog load 到内核时，通过指定pin好的map来替换内核程序初始化的映射名！
            例如：
                bpftool prog load lcm_map_pinning_save_kern.o /sys/fs/bpf/lcm_map_pinning_save  map name lcmdataset /sys/fs/bpf/lcm/my_dataset 
  
未来可以看看bpftool源码研究下。 


根据研究tc那边，在elf map增加pinging就行了，这个是
 https://blogs.oracle.com/linux/notes-on-bpf-3
 
 ```
 
 Once bpf_load.c has scanned the ELF headers, it calls bpf_create_map_node() or bpf_create_map_in_map_node() which are implemented in tools/lib/bpf/bpf.c as wrappers to the BPF_MAP_CREATE command for the SYS_BPF syscall.

Unless you are writing tc or lightweight tunnel BPF programs - which, since they implement BPF program loading themselves have their own map loading mechanisms - I'd recommend re-using this code rather than re-inventing the wheel. We can see it's generally a case of defining a map type, key/value sizes and a maximum number of entries.

Programs which use "tc"/"ip route" for loading can utilize a data structure like this (from tc_l2_redirect_kern.c):

#define PIN_GLOBAL_NS           2

struct bpf_elf_map {
        __u32 type;
        __u32 size_key;
        __u32 size_value;
        __u32 max_elem;
        __u32 flags;
        __u32 id;
        __u32 pinning;
};    

struct bpf_elf_map SEC("maps") tun_iface = {
        .type = BPF_MAP_TYPE_ARRAY,
        .size_key = sizeof(int),
        .size_value = sizeof(int),
        .pinning = PIN_GLOBAL_NS,
        .max_elem = 1,

};
The bpf_elf_map data structure mirrors that defined in https://git.kernel.org/pub/scm/network/iproute2/iproute2.git/tree/include/bpf_elf.h?h=v4.14.1.
 
 ```


内核这边可能可以用 
https://github.com/torvalds/linux/blob/master/tools/testing/selftests/bpf/progs/test_pinning.c#L8

来在内核的map不用每次新分。


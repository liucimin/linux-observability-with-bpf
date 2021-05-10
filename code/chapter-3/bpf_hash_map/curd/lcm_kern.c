





#include <linux/version.h>
#include <linux/ptrace.h>
#include <uapi/linux/bpf.h>
#include "bpf_helpers.h"

//#include "bpf_helpers.h"
//#include <linux/bpf.h>
//#include "bpf_endian.h"
//#define SEC(NAME) __attribute__((section(NAME), used))


struct bpf_map_def SEC("maps") hash_map = {
	.type = BPF_MAP_TYPE_HASH,
	.key_size = sizeof(u32),
	.value_size = sizeof(long),
	.max_entries = 2,
};


//struct bpf_map_def SEC("maps") learn_map = {
//    .type = BPF_MAP_TYPE_HASH,
//    .key_size = sizeof(int),
//    .value_size = sizeof(int),
//    .max_entries = 2
//};


//static int (*bpf_trace_printk)(const char *fmt, int fmt_size,
//                               ...) = (void *)BPF_FUNC_trace_printk;

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  
  int key = 1;
int value = 1024;
  bpf_map_update_elem(&hash_map, &key, &value, BPF_ANY);
  char msg[] = "Hello, BPF World!";
  bpf_trace_printk(msg, sizeof(msg));   //参考 https://blog.csdn.net/notbaron/article/details/80256549
  /*
  4.1     bpf_trace_printk
语法：int bpf_trace_printk(const char *fmt, int fmt_size, ...)

简单的内核printf函数，输出到/sys/kernel/debug/tracing/trace_pipe。这个在之前有描述过，其最多３个参数，智能输出%s，
而且trace_pipe是全局共享的并发输出会有问题，生产中工具使用BPF_PERF_OUTPUT()函数。

4.2     BPF_PERF_OUTPUT
通过perf ring buffer创建BPF表，将定义的事件数据输出。这个是将数据推送到用户态的建议方法。

4.3     perf_submit
语法：int perf_submit((void *)ctx, (void *)data, u32 data_size)

该函数是BPF_PERF_OUTPUT表的方法，将定义的事件数据推到用户态。
  */
  return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;


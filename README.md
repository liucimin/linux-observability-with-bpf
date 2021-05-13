<p><img align="right" src="/img/owl.png" width="150px"/></p>
<p></p>

# Linux Observability with BPF code examples

This is the companion code repo for the book [Linux Observability with BPF](https://bit.ly/bpf-safari).

We believe that even if the examples included in the book were all tested and working when we wrote them, human error is possible and technology changes.
For that reason, the purpose of this repo is to keep them as updated as possible and correct mistakes we made while writing the book.

**Nota Bene**: All the examples in this repository are adapted from the book to assume that you use the Vagrant environment we provide.
Examples can be slightly different in this repository because of that. The reason is that we didn't want to couple the book itself to Vagrant as a tool.
If you don't want a Vagrant based environment, make sure you have: [bcc](https://github.com/iovisor/bcc/blob/master/INSTALL.md) and [clang](https://clang.llvm.org/)


## Environment setup

- Please expand the details of the environment you want to work on.
- Remember that the examples have been tested on the Vagrant based environment primarily.
- Feel free to open an issue or a PR if you want to help in making this better for everyone!

  https://github.com/liucimin/linux-observability-with-bpf/blob/master/code/chapter-2/hello_world/README.md
  


</details>


Before going to the examples, it will be useful to have a copy of this repo in your environment.

```
git clone https://github.com/liucimin/linux-observability-with-bpf.git ~/linux-observability-with-bpf
```

**IMPORTANT NOTE**: The examples assume that you clone the repo in your home folder `~/linux-observability-with-bpf`, if you didn't do
please remember to change your commands!

Yay, at this point you have everything and can follow the following code examples.

## Code examples

Click on each example to follow the setup instructions.


### Chapter 2

- [Hello World](/code/chapter-2/hello_world)

### Chapter 3

- [The BPF Virtual Filesystem](/code/chapter-3/bpf_fs)

### Chapter 4

#### Probes

##### Kernel Probes
- [Kprobes](/code/chapter-4/kprobes)
- [Kretprobes](/code/chapter-4/kretprobes)

##### User-Space Probes
- [Uprobes](/code/chapter-4/uprobes)
- [Uretprobes ](/code/chapter-4/uretprobes)

##### Tracepoints
- [Tracepoints](/code/chapter-4/tracepoints)

#### User Statically Defined Tracepoints (USDT)
- [User Statically Defined Tracepoints](/code/chapter-4/usdt)

##### Visualizing Tracing Data
- [Flame Graphs](/code/chapter-4/flamegraphs)
- [Histograms](/code/chapter-4/histograms)
- [Perf Events](/code/chapter-4/histograms)

### Chapter 6 - Linux Networking and BPF

- [Packet filtering for raw sockets](/code/chapter-6/packet-filtering-raw-sockets)
- [Traffic control classifier program using cls_bpf](/code/chapter-6/tc-flow-bpf-cls)

### Chapter 7 - eXpress Data Path (XDP)

- [XDP and iproute2 as a loader](/code/chapter-7/iproute2)
- [XDP and BCC](/code/chapter-7/bcc)
- [Testing XDP programs](/code/chapter-7/prog-test-run)


### Chapter 8 - Linux Kernel security, Capabilities and Seccomp

- [Seccomp BPF filter example](/code/chapter-8/seccomp)

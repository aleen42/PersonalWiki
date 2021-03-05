## RPC (Remote Procedure Call)	[Back](./../Application.md)

- Call a procedure (subroutine) that is running on another machine.
- **NFS(Network File System)** is RPC based
- To reduce the complexity of the interface specification, only **one argument** is supported to a remote procedure.
- We can use **struct** to specify more than one argument.
- 識別:
	- Hostname(Ip Address)
	- Program Identifier(32-bits integer)
	- Procedure Identifier(32-bits integer)
- RPC includes support for looking up the port number of a remote program
- The High-Level RPC library calls support **UDP only**.
- The High-Level RPC do not support any kind of authentication.
- The Low-Level RPC supports:
	- TCP & UDP
	- Timeout values
	- Asynchronous procedure calls
	- Multi-tasking Servers
	- Broadcasting 

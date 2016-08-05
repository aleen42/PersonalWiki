##Autogen	[Back](./../Embedded_System.md)

- Autogen
	- **AutoGen** is a tool designed to simplify the creation and maintenance of programs that contain large amounts of repetitious text. It is especially valuable in programs that have several blocks of text that must be kept synchronized.
	- **.def** Files: 定義存儲性參數文件
	- **.tpl** Files: 模板文件

- 基於模塊化軟件設計的基本原則:
	1. 進行模塊化設計
	2. 進行模塊件命令交互設計
	3. 進行模塊所管理的參數設計

```def
para_manage = {
	var_type = load_complete;
	sendto_dest = "\" (1 << UNIX_DATA_RECV | (1 << UNIX_THREEG_SEND | 1 << UNIX_PPPOE)) \"";
	sendto_block = "0";
	cmd_descript = "process para manage send load parameter complete cmd to other process.";
};

category = {
	cat_name = para_manage;
	cat_descript = "para manager process";
};
category = {
	cat_name = data_recv;
	cat_descript = "data recv process";
};
category = {
	cat_name = threeg_send;
	cat_descript = "threeg send process";
};
category = {
	cat_name = para_recv;
	cat_descript = "para recv process";
category = {
	cat_name = pppoe;
	cat_descript = "pppoe process";
};
```

- AutoFSM(Automated Finite State Machine, 自動有限狀態機)
	- Input: **.fsm** Files
	- Output: **.h**, **.c** Files
- State: for every valid processing state, you must specify a state name.
- Event: for every valid event that can cause a state transition, you must specify an event name.
- Prefix: external value prefix. This will keep the generated external values disambiguated(不會混淆的). If you do not specify this, it will default to the base name of the definitions file. 
- Cookie: each of these must contain C-type plus a name suitable for use in an ANSI procedure definition. It is used to pass whatever arguments you need to the transition handling code.
- \<evt-name\>: for any event types that you would like to display in an alternate format, specify the display form with a definition of this type.
- Transition: transition entries specify which transitions are valid, based on the original state and the transition event. It may specify an advisory destination state, but if it does not, then the transition defaults to an unchanged result state. Conflicting transition specifications will silently override each other. This makes specifying all state or all event type transitions useful. 
	- Every transition must specify one or more initial state attributes (tst) and one or more transition events (tev). 
	- tst: Transition initial state(轉移初始狀態). You may specify a list of states, as in \`tst = first, second, another;', or you may specify all states with an asterisk, as in: \`tst = "*";'
	- tev: Transition event(轉移). You may specify a list of events, as in \`tev = evt-1, evt-2, evt-n;', or you may specify all events with an asterisk, as in: \`tev = "*";'
	- next: Next state(下一狀態). You may only specify one. If you do not specify it, the transition will default to not changing state.
	- ttype: Transition type(轉移類型). Occasionally, it is convenient to handle different transitions with the same code. Often, when you specify multiple states or multiple events in a single transition specification. Specifying this attribute will cause the FSM to invoke the same code. Specifying \`invalid will render the transition invalid, as if it had not been specified before. Specifying `noop will suppress the emission of code for handling the transition.
- Method: There are three FSM implementation methods supported, including no implementation. That "method" leaves it to you to supply all the code. You must set the method attribute to one of the following, or omit it entirely:
	- case: the switch statement in C. A procedure will be emitted that contains a giant switch statement. Each case element will have stylized comments that will enable any code that has been inserted there to be carried forward to new generations of the code.
	- call: Instead of containing a transition enumeration, the transition table will contain pointers to transition procedures. The main FSM processing routine will indirectly call the proper procedure for handling each transition. The called procedure will be stubbed out and contain the same type of stylized comments that the case version, above.
	- none: No implementation code will be emitted. However, the state, event, transition enumerations and the transition table are all emitted. The emitted header file will contain external declarations for the transition table and transition error procedure.

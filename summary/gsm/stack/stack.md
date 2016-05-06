## Protocol Stack   [Back](./../gsm.md)

GSM architecture is a layered model that is designed to allow communications between two different systems. The lower layers assure the services of the upper-layer protocols. Each layer passes suitable notifications to ensure the transmitted data has been formatted, transmitted, and received accurately.

The GMS protocol stacks diagram is shown below:

<img src="./gsm-protocol-stack.gif">

#### MS(Mobile Station) Protocols

Based on the interface, the GSM signaling protocol is assembled into three general layers:

- **Layer 1**: The physical layer. It uses the channel structures over the air interface.
- **Layer 2**: The data-link layer. Across the Um interface, the data-link layer is a modified version of the Link access protocol for the D channel (LAP-D) protocol used in ISDN, called Link access protocol on the Dm channel (LAP-Dm). Across the A interface, the Message Transfer Part (MTP), Layer 2 of SS7 is used.
- **Layer 3**: GSM signalling protocol's third layer is divided into three sublayers:
    - Radio Resource Management (RR)
    - Mobility Management (MM)
    - Connection Management (CM)

#### MS(Mobile Station, 移动站) to BTS(Base Transceiver Station, 基地收发机站) Protocols

The RR layer is the lower layer that manages a link, both radio and fixed, between the MS and the MSC. For this formation, the main components involved are the MS, BSS, and MSC. The responsibility of the RR layer is to manage the RR-session, the time when a mobile is in a dedicated mode, and the radio channels including the allocation of dedicated channels.

The MM layer is stacked above the RR layer. It handles the functions that arise from the mobility of the subscriber, as well as the authentication and security aspects. Location management is concerned with the procedures that enable the system to know the current location of a powered-on MS so that incoming call routing can be completed.

The CM layer is the topmost layer of the GSM protocol stack. This layer is responsible for Call Control, Supplementary Service Management, and Short Message Service Management. Each of these services are treated as individual layer within the CM layer. Other functions of the CC sub-layer include call establishment, selection of the type of service (including alternating between services during a call), and call release.

### BSC(Base Station Controller, 基站控制器) Protocols

The BSC uses a different set of protocols after receiving the data from the BTS. The Abis interface is used between the BTS and BSC. At this level, the radio resources at the lower portion of Layer 3 are changed from the RR to the Base Transceiver Station Management (BTSM). The BTS management layer is a relay function at the BTS to the BSC.


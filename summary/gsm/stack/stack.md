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




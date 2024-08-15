# chatroom_C
* 常用的 socket 有兩種，SOCK_STREAM( for TCP )、SOCK_DGRAM( for UDP )，這次的實作是使用 TCP 的 socket 來做一個簡單的聊天室

## Server主要功能
1. 在特定的 port 上進行監聽，等待 client 端連線
2. 使用者可以配置 server 端的監聽 port
3. 向連接的 client 發送登入成功的消息
4. 向已經連接到 server 的 client 端使用者發送系統消息
5. 當聊天室運行時， server 會將聊天紀錄存在 log.txt裡面，方便追蹤使用者的聊天過程

## Client主要功能
1. 運行 client 端連接到已經開啟服務的 server 端
2. 使用者可以向 server 發送消息
3. 使用者可以接受 server 發送的系統消息

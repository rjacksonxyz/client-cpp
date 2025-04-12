package main

import (
	"fmt"
	"log"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool {
		return true // Allow all connections for this example
	},
}

func handleWebSocket(w http.ResponseWriter, r *http.Request) {
	conn, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Printf("Failed to upgrade connection: %v", err)
		return
	}
	defer conn.Close()

	// Send a message every 200ms
	ticker := time.NewTicker(200 * time.Millisecond)
	defer ticker.Stop()

	for {
		select {
		case <-ticker.C:
			message := fmt.Sprintf("Server time: %v", time.Now().Format(time.RFC3339))
			err := conn.WriteMessage(websocket.TextMessage, []byte(message))
			if err != nil {
				log.Printf("Failed to write message: %v", err)
				return
			}
		}
	}
}

func main() {
	http.HandleFunc("/ws", handleWebSocket)

	fmt.Println("WebSocket server starting on :4444")
	if err := http.ListenAndServe(":4444", nil); err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}

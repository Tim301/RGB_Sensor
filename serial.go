package main

import (
	"bufio"
	"fmt"
	"io" //package for http based web programs
	"strings"

	serial "github.com/tarm/goserial"
)

type Values struct {
	Boolean bool   `json:"Boolean"`
	Color   string `json:"Color"`
	Null    string `json:"Null"`
	Number  int    `json:"Number"`
}

var s io.ReadWriteCloser

var c = &serial.Config{
	Name: "COM3",
	Baud: 9600,
	//		ReadTimeout: time.Millisecond * 5,
}

var PORTS = []string{"COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "COM10", "COM11"}

var Free = []string{}

var UsedCOM = ""

func init() {
	ScanCom()
	fmt.Println(Free)
}

func ScanCom() {
	var err error
	for _, COM := range PORTS {
		c.Name = COM
		s, err = serial.OpenPort(c)
		if err != nil {
			fmt.Println(COM + ": Not connected")
		} else {
			Free = append(Free, COM)
			fmt.Println(COM + ": Available")
			s.Close()
		}
	}
}

// Connect to COMx
func Connect(COM string) {
	var err error
	Disconnect()
	c.Name = COM
	s, err = serial.OpenPort(c)
	if err != nil {
		fmt.Println(COM + ": Problem to connect")
	} else {
		UsedCOM = COM
		fmt.Println("Connected to " + COM)
	}
}

// Disconnect from COMx
func Disconnect() {
	if UsedCOM != "" {
		s.Close()
		fmt.Println("Disconnected from " + UsedCOM)
		UsedCOM = ""
	}
}

func ReceiveFromArduino() string {
	// Receive reply
	reply := ReadArduino()
	return reply
}

func ReadArduino() string {
	keepreading := true
	data := ""

	scanner := bufio.NewScanner(s)
	for keepreading {
		scanner.Scan()
		line := scanner.Text()

		if strings.Contains(line, "!") && strings.Contains(line, "¡") {
			keepreading = false
		}
		data += line
	}
	start := strings.Index(data, "!")
	return data[start+1 : len(data)-2]
}

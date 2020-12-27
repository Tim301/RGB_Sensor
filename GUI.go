package main

import (
	"fmt"
	"fyne.io/fyne"
	"fyne.io/fyne/canvas"
	"fyne.io/fyne/cmd/fyne_demo/data"
	"fyne.io/fyne/container"
	"fyne.io/fyne/widget"
	"net/url"
	"strconv"
)

func parseURL(urlStr string) *url.URL {
	link, err := url.Parse(urlStr)
	if err != nil {
		fyne.LogError("Could not parse URL", err)
	}

	return link
}

func welcomeScreen(_ fyne.Window) fyne.CanvasObject {
	logo := canvas.NewImageFromResource(data.FyneScene)
	logo.FillMode = canvas.ImageFillContain
	if fyne.CurrentDevice().IsMobile() {
		logo.SetMinSize(fyne.NewSize(171, 125))
	} else {
		logo.SetMinSize(fyne.NewSize(228, 167))
	}

	return container.NewCenter(container.NewVBox(
		widget.NewLabelWithStyle("Welcome to the Fyne toolkit demo app", fyne.TextAlignCenter, fyne.TextStyle{Bold: true}),
		logo,
		container.NewHBox(
			widget.NewHyperlink("fyne.io", parseURL("https://fyne.io/")),
			widget.NewLabel("-"),
			widget.NewHyperlink("documentation", parseURL("https://fyne.io/develop/")),
			widget.NewLabel("-"),
			widget.NewHyperlink("sponsor", parseURL("https://github.com/sponsors/fyne-io")),
		),
	))
}

func makeTable(_ fyne.Window) fyne.CanvasObject {
	t := widget.NewTable(
		func() (int, int) { return 9, 6 },
		func() fyne.CanvasObject {
			return widget.NewLabel("Cell 000, 000")
		},
		func(id widget.TableCellID, cell fyne.CanvasObject) {
			label := cell.(*widget.Label)
			switch id.Col {
			case 0:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("N°"))
				} else {
					label.SetText(fmt.Sprintf("%d", id.Row))
				}
			case 1:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("R"))
				} else {
					label.SetText(fmt.Sprintf(strconv.Itoa(jsonOBJ[strconv.Itoa(id.Row)].R)))
				}
			case 2:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("G"))
				} else {
					label.SetText(fmt.Sprintf(strconv.Itoa(jsonOBJ[strconv.Itoa(id.Row)].G)))
				}
			case 3:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("B"))
				} else {
					label.SetText(fmt.Sprintf(strconv.Itoa(jsonOBJ[strconv.Itoa(id.Row)].B)))
				}
			case 4:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("W"))
				} else {
					label.SetText(fmt.Sprintf(strconv.Itoa(jsonOBJ[strconv.Itoa(id.Row)].W)))
				}
			case 5:
				if id.Row == 0 {
					label.SetText(fmt.Sprintf("Bat"))
				} else {
					label.SetText(fmt.Sprint(strconv.Itoa(jsonOBJ[strconv.Itoa(id.Row)].Bat)+"%"))
				}
			}
		})
	t.SetColumnWidth(0, 34)
	t.SetColumnWidth(1, 60)
	t.SetColumnWidth(2, 60)
	t.SetColumnWidth(3, 60)
	t.SetColumnWidth(4, 60)
	t.SetColumnWidth(5, 60)
	t.SetColumnWidth(6, 60)
	t.Resize(fyne.Size{300,300})
	t.Refresh()
	return t
}

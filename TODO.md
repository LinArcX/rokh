# app
-[] improve font rendering
-[] implement a mechanism to get/set active widget on the current window.

# TextInput
-[DONE] implement caret shape.
-[] add fixed property
  -[] if fixed == true, text won't exceed the boundaries of inputText.(you can just put chars depend on the width of textInput)
  -[] if fixed == false, text will add but only the section of the text that is related to the caret should be visible. other parts should be hidden but availabe in memory.
-[] when widget selected, the backgroundColor/borderColor should be change.
-[] add capability to show hint when textInput is empty.
-[] when textInput is not active it should hide caret and show hint text.
-[] implement selection feature. so end-user can select some part/whole text.
-[] implement vertical/horizontal scrollbar

-[] impelement keyboard shortcut actions in textbox including:
  -[] Ctrl-A: grab whole text
  -[] Ctrl-C: copy current selected text in TextInput and put it in system clipboard.
  -[] Ctrl-V: paste clipboard content into where caret points to.

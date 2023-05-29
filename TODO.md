# app
- improve font rendering
- implement a mechanism to get/set active widget on the current window.

# TextInput
- when widget selected, the backgroundColor/borderColor should be change.
- implement caret shape.
- implement selection feature. so end-user can select some part/whole text.
- implement vertical/horizontal scrollbar
- add wrapping property
  - if wrapping == true, text won't exceed the boundaries of inputText.
  - if wrapping == false, vertical/horizontal scrollbar should be activate.
- impelement keyboard shortcut actions in textbox including:
  - Ctrl-A: grab whole text
  - Ctrl-C: copy current selected text in TextInput and put it in system clipboard.
  - Ctrl-V: paste clipboard content into where caret points to.

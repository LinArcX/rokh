# app
- [] improve overall font rendering.
- [] implement a mechanism to get/set active widget on the current window.
- [] find a way to initialize some properties of widgets by default in cave library itself.
- [] initialize all widget with a default value before letting user create any widget.

# TextInput
- [DONE] add caret property.
  - [DONE] add caretShape property.(VERTICAL/HORIZONTAL)
  - [] add caretColor property.
  - [] add caretAnimation property.
- [] add textModel property(it should be an enum):
  - [] if textModel == SINGLE_LINE_FIXED, text won't exceed the boundaries of inputText.(you can just put chars depend on the width of textInput)
  - [] if textModel == SINGLE_LINE_FLOATING, text will add but only the section of the text that is related to the caret should be visible. other parts should be hidden but availabe in memory.
  - [] if textModel == MULTILINE_FLOATING, when each line exceed, new line will be create and new chars append to the end of new line.
    - [] implement vertical/horizontal scrollbar only in this part.
- [] when widget selected, the backgroundColor/borderColor should be change.
- [] add hint property:
  - [] if textInput is empty and it's not active hint should be show and caret should be hide.
  - [] if textInput is empty but it's active, hint should be hide and caret should be visible.
- [] implement selection feature. so end-user can select some part/whole text.
- [] impelement keyboard shortcut actions in textbox including:
  - [] Ctrl-A: grab whole text
  - [] Ctrl-C: copy current selected text in TextInput and put it in system clipboard.
  - [] Ctrl-V: paste clipboard content into where caret points to.
  - [] Ctrl-ARROW_LEFT: to move to the previous charachter.
  - [] Ctrl-ARROW_RIGHT: to move to the next charachter.
  - [] Ctrl-ARROW_TOP: to move to the top line.(if textModel == MULTILINE_FLOATING)
  - [] Ctrl-ARROW_BOTTOM: to move to the bottom line.(if textModel == MULTILINE_FLOATING)

open ReasonReact;

type message = string;
type state = {messages: list(message)};
type action =
  | Add(message);

let component = reducerComponent("Example");

let make = _children => {
  ...component,
  initialState: () => {messages: []},
  reducer: (action, state) =>
    switch (action) {
    | Add(message) => Update({messages: [message, ...state.messages]})
    },
  render: self =>
    <div>
      <button onClick=(_event => self.send(Add("Hello")))>
        (string("button"))
      </button>
      (
        array(
          Array.of_list(
            self.state.messages |> List.map(message => <div> (string(message)) </div>),
          ),
        )
      )
    </div>,
};
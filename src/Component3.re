open ReasonReact;

type name = string;
type state = {names: list(name)};
type action =
  | Add(name);

let component = reducerComponent("Example");

let make = _children => {
  ...component,
  initialState: () => {names: []},
  reducer: (action, state) =>
    switch (action) {
    | Add(name) => Update({names: [name, ...state.names]})
    },
  render: self =>
    <div>
      <button onClick=(_event => self.send(Add("harsh")))>
        (string("button"))
      </button>
      (
        array(
          Array.of_list(
            self.state.names |> List.map(name => <div> (string(name)) </div>),
          ),
        )
      )
      <Component1 message="hey all" />
    </div>,
};
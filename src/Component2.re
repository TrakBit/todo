type state = {
  count: int,
  show: bool
};

type action =
  | Add
  | Remove
  | Toggle;

let component = ReasonReact.reducerComponent("Example");

let make = (~greeting, _children) => {
  ...component,
  initialState: () => {count: 0, show: true},
  reducer: (action, state) =>
    switch (action) {
    | Add => ReasonReact.Update({...state, count: state.count + 1})
    | Remove => ReasonReact.Update({...state, count: state.count - 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    },
  render: self => {
    let add = "Add: " ++ string_of_int(self.state.count);
    let subtract = "Subtract: " ++ string_of_int(self.state.count);
    <div>
      <title />
      <button onClick=(_event => self.send(Add))>
        (ReasonReact.string(add))
      </button>
      <button onClick=(_event => self.send(Remove))>
        (ReasonReact.string(subtract))
      </button>
      <button onClick=(_event => self.send(Toggle))>
        (ReasonReact.string("Toggle greeting"))
      </button>
      (self.state.show ? ReasonReact.string(greeting) : ReasonReact.null)
    </div>;
  }
};

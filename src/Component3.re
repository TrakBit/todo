type name = {name: string};

type state = {names: list(name)};

type action =
  | Add(name);

let component = ReasonReact.reducerComponent("Example");

let make = _ => {
  ...component,
  initialState: () => {names: []},
  reducer: (action, state) =>
    switch (action) {
    | Add(name) => ReasonReact.Update({names: [name, ...state.names]})
    },
  render: self =>
    <div>
      <button onClick=(_event => self.send(Add({name: "harsh"})))>
        (ReasonReact.string("button"))
      </button>
      (
        ReasonReact.array(
          Array.of_list(
            self.state.names
            |> List.map(item => <div> (ReasonReact.string(item.name)) </div>),
          ),
        )
      )
    </div>,
};
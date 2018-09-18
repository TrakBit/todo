type name = {name: string};

type state = {names: list(string)};

type action =
  | Add(string);

let component = ReasonReact.reducerComponent("Example");

let make = (_) => {
  ...component,
  initialState: () => {names: []},
  reducer: (action, state) =>
    switch (action) {
    | Add(string) => ReasonReact.Update({names: [ string, ...state.names,]})
    },
  render: self => {
    <div>
      <button onClick=(_event => self.send(Add("harsh")))>
        (ReasonReact.string("button"))
      </button>
      (ReasonReact.array(Array.of_list(self.state.names |>  List.map((_)=> <div>(ReasonReact.string("hey"))</div>))))
    </div>
  },
};

 
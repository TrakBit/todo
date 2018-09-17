type name = {name: string};

type state = {names: array(string)};

type action =
  | Add(string);

let component = ReasonReact.reducerComponent("Example");

let make = (_) => {
  ...component,
  initialState: () => {names: [||]},
  reducer: (action, state) =>
    switch (action) {
    | Add(string) => ReasonReact.Update({names: state.names |> Js.Array.concat([|string|])})
    },
  render: self => {
    <div>
      <button onClick=(_event => self.send(Add("harsh")))>
        (ReasonReact.string("button"))
      </button>
      (ReasonReact.array(self.state.names |>  Js.Array.map((_)=> <div>(ReasonReact.string("hey"))</div>)))
    </div>
  },
};


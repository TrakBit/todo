open Fetch;
open Json;

type message = {
  id: int,
  msgbody: string,
};

let url = "http://www.mocky.io/v2/5bb2211b330000650011c7d6";

type messages = list(message);

type state = messages;

type action =
  | MsgFetching
  | MsgFetched(messages)
  | MsgFailed;

module DecodeData = {
  let message = json : message =>
    Decode.{
      id: json |> field("id", int),
      msgbody: json |> field("msgbody", string),
    };
  let messages = Decode.list(message);
};

let component = ReasonReact.reducerComponent("Example");

let make = _children => {
  ...component,
  initialState: () => [],
  reducer: (action, _state) =>
    switch (action) {
    | MsgFetching =>
      ReasonReact.UpdateWithSideEffects(
        [],
        (
          self =>
            Js.Promise.(
              fetch(url)
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> DecodeData.messages
                   |> (messages => self.send(MsgFetched(messages)))
                   |> resolve
                 )
              |> catch(_err => Js.Promise.resolve(self.send(MsgFailed)))
              |> ignore
            )
        ),
      )
    | MsgFetched(messages) => ReasonReact.Update(messages)
    | MsgFailed => ReasonReact.Update([])
    },
  render: self =>
    <div>
      <button onClick=(_event => self.send(MsgFetching))>
        (ReasonReact.string("Fetch Messages"))
      </button>
      <div>
        (
          ReasonReact.array(
            Array.of_list(
              self.state
              |> List.map(message =>
                   <li key=(string_of_int(message.id))>
                     (ReasonReact.string(message.msgbody))
                   </li>
                 ),
            ),
          )
        )
      </div>
    </div>,
};
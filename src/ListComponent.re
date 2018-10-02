open Fetch;
open Json;

type message = {
  id: int,
  msgbody: string,
};

let url = "http://www.mocky.io/v2/5bb2211b330000650011c7d6";

type messages = list(message);

type state =
  | Loading
  | Loaded(messages)
  | Error;

type action =
  | MsgFetch
  | MsgFetched(messages)
  | MsgFailed;

module DecodeData = {
  let message = message : message =>
    Decode.{
      id: field("id", int, message),
      msgbody: field("msgbody", string, message),
    };
  let messages = json : messages =>
    Decode.(list(message, json) |> List.map(message => message));
};

let component = ReasonReact.reducerComponent("Example");

let make = _children => {
  ...component,
  initialState: () => Loading,
  reducer: (action, _state) =>
    switch (action) {
    | MsgFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
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
    | MsgFetched(messages) => ReasonReact.Update(Loaded(messages))
    | MsgFailed => ReasonReact.Update(Error)
    },
  render: self =>
    <div>
      <button onClick=(_event => self.send(MsgFetch))>
        (ReasonReact.string("Fetch Messages"))
      </button>
      (
        switch (self.state) {
        | Loading => <div> (ReasonReact.string("Loading...")) </div>
        | Loaded(messages) =>
          <div>
            (
              ReasonReact.array(
                Array.of_list(
                  messages
                  |> List.map(message =>
                       <li key=(string_of_int(message.id))>
                         (ReasonReact.string(message.msgbody))
                       </li>
                     ),
                ),
              )
            )
          </div>
        | Error => <div> (ReasonReact.string("Error")) </div>
        }
      )
    </div>,
};
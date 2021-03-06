// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var url = "http://www.mocky.io/v2/5bb2211b330000650011c7d6";

function message(json) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.$$int, json),
          /* msgbody */Json_decode.field("msgbody", Json_decode.string, json)
        ];
}

function messages(param) {
  return Json_decode.list(message, param);
}

var DecodeData = /* module */[
  /* message */message,
  /* messages */messages
];

var component = ReasonReact.reducerComponent("Example");

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", undefined, React.createElement("button", {
                              onClick: (function () {
                                  return Curry._1(self[/* send */3], /* MsgFetching */0);
                                })
                            }, "Fetch Messages"), React.createElement("div", undefined, $$Array.of_list(List.map((function (message) {
                                        return React.createElement("li", {
                                                    key: String(message[/* id */0])
                                                  }, message[/* msgbody */1]);
                                      }), self[/* state */1]))));
            }),
          /* initialState */(function () {
              return /* [] */0;
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, _) {
              if (typeof action === "number") {
                if (action !== 0) {
                  return /* Update */Block.__(0, [/* [] */0]);
                } else {
                  return /* UpdateWithSideEffects */Block.__(2, [
                            /* [] */0,
                            (function (self) {
                                fetch(url).then((function (prim) {
                                            return prim.json();
                                          })).then((function (json) {
                                          var messages = Json_decode.list(message, json);
                                          return Promise.resolve(Curry._1(self[/* send */3], /* MsgFetched */[messages]));
                                        })).catch((function () {
                                        return Promise.resolve(Curry._1(self[/* send */3], /* MsgFailed */1));
                                      }));
                                return /* () */0;
                              })
                          ]);
                }
              } else {
                return /* Update */Block.__(0, [action[0]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.url = url;
exports.DecodeData = DecodeData;
exports.component = component;
exports.make = make;
/* component Not a pure module */

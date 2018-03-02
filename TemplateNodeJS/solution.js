const readline = require("readline-sync");

/////////////// ignore above this line ////////////////////

function biggerIsGreater(w) {
  return "test";
}

function main() {
  var T = readline.question("T? ");

  for (var i = 0; i < T; ++i) {
    var input = readline.question(i + "? ");
    var result = biggerIsGreater(input);
    console.log(result);
  }
}

main();

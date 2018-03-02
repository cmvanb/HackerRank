const readline = require("readline-sync");

/////////////// ignore above this line ////////////////////

function biggerIsGreater(w) {
  // discard strings of length 1 or less
  if (w.length <= 1) {
    return "no answer";
  }
  // find largest suffix containing elements in decreasing order
  let lastIndex = w.length - 1;
  let i = lastIndex;
  while (w[i - 1] >= w[i]) {
    if (i == 1) {
      // word is already greatest value
      return "no answer";
    }
    --i;
  }
  let suffix = w.substr(i);
  let leftIndex = i - 1;
  // find smallest element in suffix that is greater than left
  let smallestIndex = (seq => {
    for (let j = seq.length - 1; j >= 0; --j) {
      if (seq[j] > w[leftIndex]) {
        return j + i;
      }
    }
  })(suffix);
  // swap smallest with left
  let swapped = swapChars(w, leftIndex, smallestIndex);
  // sort new suffix
  let result =
    swapped.substr(0, leftIndex + 1) +
    swapped
      .substr(leftIndex + 1)
      .split("")
      .reverse()
      .join("");
  return result;
}

function swapChars(str, index0, index1) {
  let result = str.split("");
  result[index0] = str.charAt(index1);
  result[index1] = str.charAt(index0);
  return result.join("");
}

function main() {
  let T = readline.question("");
  let w = [];

  for (let i = 0; i < T; ++i) {
    w.push(readline.question(""));
  }

  for (let i = 0; i < T; ++i) {
    let result = biggerIsGreater(w[i]);
    console.log(result);
  }
}

main();

import { read } from "./reader.js";
import { p2 } from "./day4.js";

async function main() {
    let input = await read(null);
    let res = p2(input);
    console.log({ res });
}

main();

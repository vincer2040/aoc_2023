import { createInterface } from "readline";
import { readFileSync } from "fs";

/**
 * @param {string | null} path
 * @returns {Promise<string>} file contents
 */
export function read(path) {
    if (path == null) {
        const r1 = createInterface({
            input: process.stdin,
            output: process.stdout,
        });

        return new Promise((res) => {
            let lines = "";
            r1.on("line", (line) => {
                lines += line + "\n";
            })
            r1.on("close", () => {
                res(lines);
            })
        });
    } else {
        let contents = readFileSync(path, "utf8");
        return new Promise((res) => { res(contents) });
    }
}

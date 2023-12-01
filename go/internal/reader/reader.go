package reader

import (
	"bufio"
	"os"
)

func ReadFile(path *string) (string, error) {
    if path == nil {
        scanner := bufio.NewScanner(os.Stdin);
        res := "";
        for scanner.Scan() {
            line := scanner.Text();
            res += line + "\n";
        }
        return res, nil;
    } else {
        data, err := os.ReadFile(*path)
        if err != nil {
            return "", err
        }
        return string(data), nil
    }
}

declare type Seed = {
    start: number,
    length: number,
};

declare type RangeT = {
    dst: number,
    src: number,
    range: number,
};

declare type MapItem = {
    from: string,
    to: string,
    map: RangeT[],
};

declare type DataMap = Record<string, MapItem>;

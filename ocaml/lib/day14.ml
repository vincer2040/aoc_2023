module StringList = struct
  type t = string list

  let compare a b = List.compare String.compare a b
end

module StringListMap = Map.Make (StringList)

let rec find_spot platform platform_idx row_idx =
  if platform_idx < 0
  then 0
  else (
    let ch = String.get (List.nth platform platform_idx) row_idx in
    if ch == '#' || ch == 'O'
    then platform_idx + 1
    else find_spot platform (platform_idx - 1) row_idx)
;;

let create_new_platform platform spots cur_idx =
  let p =
    List.mapi
      (fun row_idx row ->
        let new_row =
          String.mapi
            (fun i ch ->
              let spot = List.nth spots i in
              if row_idx == cur_idx
              then if spot == -1 || spot == row_idx then ch else '.'
              else if spot == row_idx
              then 'O'
              else ch)
            row
        in
        new_row)
      platform
  in
  p
;;

let rev_string str = List.rev str |> List.to_seq |> String.of_seq

let rec rotate old new_platform idx =
  let len = String.length (List.nth old 0) in
  if idx >= len
  then List.rev new_platform
  else (
    let l = List.map (fun row -> String.get row idx) old in
    let new_row = rev_string l in
    rotate old (new_row :: new_platform) (idx + 1))
;;

let rec tilt platform idx =
  if idx >= List.length platform
  then platform
  else (
    let row = List.nth platform idx in
    let spots =
      String.to_seq row
      |> List.of_seq
      |> List.mapi (fun i ch ->
        if ch == '.' || ch == '#' then -1 else find_spot platform (idx - 1) i)
    in
    let new_platform = create_new_platform platform spots idx in
    tilt new_platform (idx + 1))
;;

let cycle input =
  let north_tilt = tilt input 0 in
  let w = rotate north_tilt [] 0 in
  let west_tilt = tilt w 0 in
  let s = rotate west_tilt [] 0 in
  let south_tilt = tilt s 0 in
  let e = rotate south_tilt [] 0 in
  let east_rotate = tilt e 0 in
  let r = rotate east_rotate [] 0 in
  r
;;

let calc platform =
  let _, res =
    List.fold_left
      (fun (idx, acc) row ->
        let amt_rocks =
          String.fold_left
            (fun num_rocks ch -> if ch == 'O' then num_rocks + 1 else num_rocks)
            0
            row
        in
        idx + 1, acc + (amt_rocks * (idx + 1)))
      (0, 0)
      (List.rev platform)
  in
  res
;;

let rec run platform map i end_num =
  if i >= end_num
  then platform
  else (
    let x = i + 1 in
    let new_platform = cycle platform in
    if StringListMap.mem new_platform map
    then (
      let from_map = StringListMap.find new_platform map in
      let cycle_length = x - from_map in
      let amt = (end_num - x) / cycle_length in
      let new_i = x + (amt * cycle_length) in
      let new_map = StringListMap.add new_platform new_i map in
      run new_platform new_map new_i end_num)
    else (
      let new_map = StringListMap.add new_platform x map in
      run new_platform new_map x end_num))
;;

let p1 input =
  let input = String.trim input |> String.split_on_char '\n' in
  let platform = tilt input 0 in
  let res = calc platform in
  res
;;

let p2 input =
  flush stdout;
  let input = String.trim input |> String.split_on_char '\n' in
  let c = run input StringListMap.empty 0 1000000000 in
  let res = calc c in
  res
;;

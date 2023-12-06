type race =
  { time : int
  ; distance : int
  }

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let replace str old new_sub =
  let re = Re.Posix.compile_pat old in
  Re.replace_string re ~by:new_sub str
;;

let get_possible_ways_to_win time dist =
  let d = (time * time) - (4 * dist) in
  let sqrt_d = int_of_float (sqrt (float_of_int d)) in
  if sqrt_d * sqrt_d = d
  then sqrt_d - 1
  else sqrt_d + 1 - (time mod 2 lxor (sqrt_d mod 2))
;;

let p1 input =
  let split = String.split_on_char '\n' input |> List.filter filter_none in
  let times =
    replace (List.nth split 0) "Time: " ""
    |> String.split_on_char ' '
    |> List.filter filter_none
    |> List.map (fun time -> int_of_string time)
  in
  let distances =
    replace (List.nth split 1) "Distance: " ""
    |> String.split_on_char ' '
    |> List.filter filter_none
    |> List.map (fun dist -> int_of_string dist)
  in
  let races =
    List.mapi
      (fun i time ->
        let distance = List.nth distances i in
        { time; distance })
      times
  in
  let result =
    List.fold_left
      (fun res race ->
        let possible = get_possible_ways_to_win race.time race.distance in
        res * possible)
      1
      races
  in
  result
;;

let p2 input =
  let split = String.split_on_char '\n' input |> List.filter filter_none in
  let time =
    replace (List.nth split 0) "Time: " ""
    |> String.split_on_char ' '
    |> List.filter filter_none
    |> List.fold_left (fun acc time -> acc ^ time) ""
    |> int_of_string
  in
  let distance =
    replace (List.nth split 1) "Distance: " ""
    |> String.split_on_char ' '
    |> List.filter filter_none
    |> List.fold_left (fun acc dist -> acc ^ dist) ""
    |> int_of_string
  in
  get_possible_ways_to_win time distance
;;

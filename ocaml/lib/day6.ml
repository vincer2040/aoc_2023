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
        let hold_times = List.init (race.time + 1) (fun i -> i) in
        let race_time = race.time in
        let record_distance = race.distance in
        let num_ways_to_win =
          List.fold_left
            (fun acc hold_time ->
              let remaining_time = race_time - hold_time in
              let dist_travaled = hold_time * remaining_time in
              if dist_travaled > record_distance then acc + 1 else acc)
            0
            hold_times
        in
        if num_ways_to_win > 0 then num_ways_to_win * res else res)
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
  let hold_times = List.init (time + 1) (fun i -> i) in
  let result =
    List.fold_left
      (fun acc hold_time ->
        let remaining_time = time - hold_time in
        let dist_travaled = hold_time * remaining_time in
        if dist_travaled > distance then acc + 1 else acc)
      0
      hold_times
  in
  result
;;

let p1 input =
  String.split_on_char '\n' input
  |> List.filter (fun line ->
    match line with
    | "" -> false
    | _ -> true)
  |> List.fold_left
       (fun acc line ->
         let card_game = String.split_on_char ':' line in
         let game =
           List.nth card_game 1 |> String.trim |> String.split_on_char '|'
         in
         let winning_numbers =
           List.nth game 0
           |> String.trim
           |> String.split_on_char ' '
           |> List.filter (fun s ->
             match s with
             | " " -> false
             | "" -> false
             | _ -> true)
           |> List.map (fun num -> String.trim num |> int_of_string)
         in
         let to_check =
           List.nth game 1
           |> String.trim
           |> String.split_on_char ' '
           |> List.filter (fun s ->
             match s with
             | " " -> false
             | "" -> false
             | _ -> true)
           |> List.map (fun num -> String.trim num |> int_of_string)
         in
         let num_points =
           List.fold_left
             (fun acc winning_num ->
               try
                 let _ =
                   List.find (fun check -> winning_num == check) to_check
                 in
                 if acc == 0 then 1 else acc * 2
               with
               | Not_found -> acc)
             0
             winning_numbers
         in
         acc + num_points)
       0
;;

let p2 input =
  let lines =
    String.split_on_char '\n' input
    |> List.filter (fun line ->
      match line with
      | "" -> false
      | _ -> true)
  in
  let lines_len = List.length lines in
  let played = Array.make lines_len 0 in
  List.iteri
    (fun i line ->
      let x = played.(i) in
      played.(i) <- x + 1;
      let card_game = String.split_on_char ':' line in
      let card =
        List.nth card_game 0
        |> String.split_on_char ' '
        |> List.filter (fun s ->
          match s with
          | " " -> false
          | "" -> false
          | _ -> true)
      in
      let card_num = List.nth card 1 |> String.trim |> int_of_string in
      let game =
        List.nth card_game 1 |> String.trim |> String.split_on_char '|'
      in
      let winning_numbers =
        List.nth game 0
        |> String.trim
        |> String.split_on_char ' '
        |> List.filter (fun s ->
          match s with
          | " " -> false
          | "" -> false
          | _ -> true)
        |> List.map (fun num -> String.trim num |> int_of_string)
      in
      let to_check =
        List.nth game 1
        |> String.trim
        |> String.split_on_char ' '
        |> List.filter (fun s ->
          match s with
          | " " -> false
          | "" -> false
          | _ -> true)
        |> List.map (fun num -> String.trim num |> int_of_string)
      in
      let num_found =
        List.fold_left
          (fun acc winning_num ->
            try
              let _ = List.find (fun check -> winning_num == check) to_check in
              acc + 1
            with
            | Not_found -> acc)
          0
          winning_numbers
      in
      let list_from_num_found =
        List.init num_found (fun i -> card_num + i + 1)
      in
      List.iteri
        (fun j _ ->
          let p = played.(i) in
          let c = played.(j + i + 1) in
          played.(j + i + 1) <- p + c)
        list_from_num_found)
    lines;
  Array.fold_left (fun acc p -> acc + p) 0 played
;;

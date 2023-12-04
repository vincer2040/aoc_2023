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
  let copies = Hashtbl.create 10 in
  String.split_on_char '\n' input
  |> List.filter (fun line ->
    match line with
    | "" -> false
    | _ -> true)
  |> List.fold_left
       (fun acc line ->
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
         let times_should_play =
           match Hashtbl.mem copies card_num with
           | false -> 1
           | true -> Hashtbl.find copies card_num + 1
         in
         let num_found =
           List.fold_left
             (fun acc winning_num ->
               try
                 let _ =
                   List.find (fun check -> winning_num == check) to_check
                 in
                 acc + 1
               with
               | Not_found -> acc)
             0
             winning_numbers
         in
         let list_from_num_found =
           List.init num_found (fun i -> card_num + i + 1)
         in
         let list_from_should_play = List.init times_should_play (fun i -> i) in
         if times_should_play == 1
         then
           List.iter
             (fun n ->
               if Hashtbl.mem copies n
               then (
                 let old = Hashtbl.find copies n in
                 Hashtbl.replace copies n (old + 1))
               else Hashtbl.add copies n 1)
             list_from_num_found
         else
           List.iter
             (fun _ ->
               List.iter
                 (fun n ->
                   if Hashtbl.mem copies n
                   then (
                     let old = Hashtbl.find copies n in
                     Hashtbl.replace copies n (old + 1))
                   else Hashtbl.add copies n 1)
                 list_from_num_found)
             list_from_should_play;
         acc + times_should_play)
       0
;;

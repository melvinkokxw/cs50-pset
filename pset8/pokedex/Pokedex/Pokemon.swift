//
//  Pokemon.swift
//  Pokedex
//
//  Created by Melvin Kok on 29/12/20.
//

import Foundation

struct PokemonList: Codable {
    let results: [Pokemon]
}

struct Pokemon: Codable {
    let name: String
//    let number: Int
    let url: String
}

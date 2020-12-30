import Foundation

struct PokemonListResults: Codable {
    let results: [PokemonListResult]
}

struct PokemonListResult: Codable {
    let name: String
    let url: URL
}

struct PokemonResult: Codable {
    let id: Int
    let name: String
    let types: [PokemonTypeEntry]
    let sprites: PokemonSprites
}

struct PokemonTypeEntry: Codable {
    let slot: Int
    let type: PokemonType
}

struct PokemonType: Codable {
    let name: String
}

struct PokemonSprites: Codable {
    let front_default: URL
}

struct PokemonSpeciesResult: Codable {
    let flavor_text_entries: [PokemonFlavorText]
}

struct PokemonFlavorText: Codable {
    let flavor_text: String
    let language: PokemonLanguage
}

struct PokemonLanguage: Codable {
    let name: String
}
